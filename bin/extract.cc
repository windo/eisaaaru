#include <boost/program_options.hpp>
#include <iostream>
#include <libgen.h>
#include <sstream>
#include <stdlib.h>
#include <taglib/chapterframe.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>

namespace po = boost::program_options;

std::string format_hms(int seconds) {
  std::ostringstream hms;
  if(seconds >= 3600) {
    auto hours = seconds / 3600;
    hms << hours << ":";
    seconds -= hours * 3600;
  }
  if(seconds >= 60) {
    auto minutes = seconds / 60;
    hms << minutes << ":";
    seconds -= minutes * 60;
  }
  hms << seconds;
  return hms.str();
}

std::string get_basename(std::string file_name) {
  char *butchered_file_name = (char*) malloc(file_name.size());
  if(butchered_file_name == NULL) {
    return "";
  }
  auto i = 0;
  for (auto p = file_name.begin(); p != file_name.end(); ++p, ++i) {
    butchered_file_name[i] = *p;
  }
  return basename(butchered_file_name);
}

std::string get_chapters(TagLib::ID3v2::FrameList chapter_frames) {
  std::ostringstream chapters;
  for(auto c = chapter_frames.begin(); c != chapter_frames.end(); ++c) {
    auto chapter = dynamic_cast<TagLib::ID3v2::ChapterFrame*> (*c);
    chapters << "  1. " << chapter->embeddedFrameListMap()["TIT2"][0]->toString().to8Bit(true) << std::endl;
  }
  return chapters.str();
}

int main(int argc, char **argv) {
  po::options_description desc;
  desc.add_options()
    ("input-file,i", po::value<std::string>(), "file to process")
    ;

  po::positional_options_description p;
  p.add("input-file", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).
      options(desc).positional(p).run(), vm);
  po::notify(vm);

  if(vm.count("input-file") != 1) {
    std::cout << desc;
    return 1;
  }
  auto file_name = vm["input-file"].as<std::string>();

  TagLib::MPEG::File f(file_name.c_str());
  if(!f.hasID3v2Tag()) {
    std::cout << "Expecting ID3v2 tag." << std::endl;;
    return 1;
  }
  /*
   * audio: "podcast_siimuga_edit_1.mp3"
   * audio_length: 16789129
   * audio_duration: "46:36"
   */
  std::cout << "---" << std::endl;
  std::cout << "title: \"" << f.tag()->title().to8Bit(true) << "\"" << std::endl;
  std::cout << "audio: \"" << get_basename(file_name) << "\"" << std::endl;
  std::cout << "audio_length: " << f.length() << std::endl;
  std::cout << "audio_duration: \"" << format_hms(f.audioProperties()->lengthInSeconds()) << "\"" << std::endl;
  std::cout << "---" << std::endl;
  std::cout << "Teemad:" << std::endl << std::endl;
  std::cout << get_chapters(f.ID3v2Tag()->frameListMap()["CHAP"]);
}