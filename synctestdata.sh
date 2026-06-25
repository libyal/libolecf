#!/bin/sh
# Script that synchronizes the local test data

TESTS_INPUT_DIRECTORY="tests/input"
TEST_SET="public"
TEST_FILES="1b4dd67f29cb1962.automaticDestinations-ms 9d1f905ce5044aee.automaticDestinations-ms"

mkdir -p "${TESTS_INPUT_DIRECTORY}/${TEST_SET}"

for TEST_FILE in ${TEST_FILES}
do
	URL="https://raw.githubusercontent.com/log2timeline/plaso/refs/heads/main/test_data/automaticDestinations-ms/${TEST_FILE}"

	curl -L -o "${TESTS_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL}
done
