#!/bin/bash

name=$1
path="static/audio/$name"
size=$(stat --printf "%s\n" $path)
total_seconds=$(mp3info -p "%S\n" $path)

seconds=$total_seconds
hours=$(($seconds / 3600))
seconds=$(($seconds - $hours * 3600))
minutes=$(($seconds / 60))
seconds=$(($seconds - $minutes * 60))
if [ "$hours" -gt 0 ]; then
  duration="${hours}:"
fi
if [ "$minutes" -gt 0 ]; then
  duration="${duration}${minutes}:"
fi
duration="${duration}${seconds}"

echo "audio: \"$name\""
echo "audio_length: $size"
echo "audio_duration: \"$duration\""
