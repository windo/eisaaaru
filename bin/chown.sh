#!/bin/sh

cd $(dirname $(readlink -f $0))/..
dirs="public staging content static resources layouts archetypes"

find $dirs ! -group eisaaaru | xargs --no-run-if-empty chgrp eisaaaru
find $dirs ! -perm -g+w | xargs --no-run-if-empty chmod g+w
