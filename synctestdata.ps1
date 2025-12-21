# Script that synchronizes the local test data
#
# Version: 20251217

$Repository = "log2timeline/plaso"
$TestDataPath = "test_data/automatic_destinations"
$TestSet = "public"
$TestInputDirectory = "tests/input"
$TestFiles = "1b4dd67f29cb1962.automaticDestinations-ms 9d1f905ce5044aee.automaticDestinations-ms"

If (-Not (Test-Path ${TestInputDirectory}))
{
	New-Item -Name ${TestInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$Url = "https://raw.githubusercontent.com/${Repository}/refs/heads/main/${TestDataPath}/${TestFile}"

	Invoke-WebRequest -Uri ${Url} -OutFile "${TestInputDirectory}\${TestSet}\${TestFile}"
}

