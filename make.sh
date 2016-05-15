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
SCR_FILES+=(NoteSequence.c)

# Base Command
BUILD_CMD=(gcc)

# Add Source Files
BUILD_CMD+=(${SRC_FILES[@]})

# Add Output File
BUILD_CMD+=(-o "\"${OUTPUT_BIN}\"")

# Add Options
BUILD_CMD+=(${BUILD_OPTS})

# Validations
[ ! -d "${BIN_DIR}" ] && mkdir "${BIN_DIR}"

echo ${BUILD_CMD[@]}
eval ${BUILD_CMD[@]}
