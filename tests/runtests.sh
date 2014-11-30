#! /bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${DIR}
LD_LIBRARY_PATH=${DIR}/../src:/home/aetf/lib ${DIR}/tests 1>&2
