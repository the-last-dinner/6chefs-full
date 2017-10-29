#!/bin/sh

ROOT_PATH=`pwd`

## 原始的だけど、シリーズごとにコメントアウト変える
# RESOUCES_PATH=${ROOT_PATH}/../../Resources/common
# RESOUCES_PATH=${ROOT_PATH}/../../Resources/6chefs
RESOUCES_PATH=${ROOT_PATH}/../../Resources/6chefs2
TMP_PATH=${ROOT_PATH}/tmp

# generate target list of encryption
for target in config event csv save; do
    ls ${RESOUCES_PATH}/${target} > ${TMP_PATH}/${target}.list
done

# output root path
echo "${RESOUCES_PATH}/" > ${TMP_PATH}/root_path.txt
