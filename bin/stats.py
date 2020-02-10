#!/usr/bin/env python

import collections
import os
import os.path
import re

ROOT = '/var/lib/awstats'


def main():
  downloads = collections.defaultdict(int)

  for stat_file in os.listdir(ROOT):
    if not stat_file.endswith('p6drad-teel.txt'):
      # Only look at full stats files for p6drad-teel.net
      continue

    with open(os.path.join(ROOT, stat_file), 'r') as f:
      for l in f.readlines():
        if not 'audio/eisaaaru' in l:
          # Only look at audio/eisaaru
          continue

        parts = l.split(' ')
        url = os.path.basename(parts[0])
        download_count = int(parts[1])
        downloads[url] += download_count

  for url in sorted(downloads.keys(), key=lambda f: int(re.match(r'.*?([0-9]+).mp3', f).group(1)), reverse=True):
    print('%s %d' % (url, downloads[url]))


if __name__ == '__main__':
  main()
