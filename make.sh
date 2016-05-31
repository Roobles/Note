#!/bin/bash

# Constants
BIN_DIR='bin'
OUTPUT_BIN_NAME='music'

# Concats
OUTPUT_BIN="${BIN_DIR}/${OUTPUT_BIN_NAME}"

# Options
BUILD_OPTS=()
BUILD_OPTS+=(-g)

# Source Files
SRC_FILES=()
SRC_FILES+=(music.c)
SRC_FILES+=(wav.c)
SRC_FILES+=(note.c)
SRC_FILES+=(tempo.c)
SRC_FILES+=(score.c)
SRC_FILES+=(musician.c)
SRC_FILES+=(instrument.c)
SRC_FILES+=(notesequence.c)
SRC_FILES+=(musicsequence.c)
SRC_FILES+=(sampledefinition.c)

# Libraries
SRC_LIB=()
SRC_LIB+=(m)

# Base Command
BUILD_CMD=(gcc)

# Add Source Files
BUILD_CMD+=(${SRC_FILES[@]})

# Add Output File
BUILD_CMD+=(-o "\"${OUTPUT_BIN}\"")

# Add Options
BUILD_CMD+=(${BUILD_OPTS})

for lib in ${SRC_LIB[@]}; do
  BUILD_CMD+=(-l${lib})
done

# Validations
[ ! -d "${BIN_DIR}" ] && mkdir "${BIN_DIR}"

echo ${BUILD_CMD[@]}
eval ${BUILD_CMD[@]}
