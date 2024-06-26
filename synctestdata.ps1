# Script that synchronizes the local test data
#
# Version: 20230709

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
	$Url = "https://github.com/log2timeline/plaso/blob/main/test_data/automatic_destinations/${TestFile}?raw=true"

	Invoke-WebRequest -Uri ${Url} -OutFile "${TestInputDirectory}\${TestSet}\${TestFile}"
}

