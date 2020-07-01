#!/bin/sh

cd $(dirname $(readlink -f $0))/..
dirs="public staging content static resources layouts archetypes"

find $dirs | xargs chgrp eisaaaru
find $dirs -type f | xargs chmod g+w
find $dirs -type d | xargs chmod g+s
