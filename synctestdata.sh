#!/bin/sh
# Script that synchronizes the local test data
#
# Version: 20251217

REPOSITORY="log2timeline/plaso";
TEST_DATA_PATH="test_data/automatic_destinations";
TEST_SET="public";
TEST_INPUT_DIRECTORY="tests/input";
TEST_FILES="1b4dd67f29cb1962.automaticDestinations-ms 9d1f905ce5044aee.automaticDestinations-ms";

mkdir -p "${TEST_INPUT_DIRECTORY}/${TEST_SET}";

for TEST_FILE in ${TEST_FILES};
do
	URL="https://raw.githubusercontent.com/${REPOSITORY}/refs/heads/main/${TEST_DATA_PATH}/${TEST_FILE}";

	curl -L -o "${TEST_INPUT_DIRECTORY}/${TEST_SET}/${TEST_FILE}" ${URL};
done

