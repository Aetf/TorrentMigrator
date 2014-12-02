#! /bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${DIR}
rm -rf data/libtorrent data/uTorrent 2>&1 > /dev/null
unzip data/libtorrent.zip -d data > /dev/null
unzip data/uTorrent.zip -d data > /dev/null
LD_LIBRARY_PATH=${DIR}/../src:/home/aetf/lib ${DIR}/tests 1>&2
