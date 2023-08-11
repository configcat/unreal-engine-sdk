param (
    [string]$portFolder,
    [string]$patchFile
)

# Helper function which returns the number of the last line containing the occurance of a certain pattern
function GetLastOccurange {
    param (
        $content,
        $regexMatch
    )

    $lastOccuranceLine = -1

    foreach($line in $fileContent) {
        if($line -match $regexMatch){
            $lastOccuranceLine = ($fileContent | select-string $line).LineNumber
        }
    }

    return $lastOccuranceLine
}

Write-Host Copying $patchFile to $portFolder
Copy-Item $patchFile -Destination $portFolder

$patchToAdd = "`r`n        ${[System.IO.Path]::GetFileName($patchFile)}"
$file = "$portFolder\portfile.cmake"
$fileContent = Get-Content $file

$lastPatchLine =  GetLastOccurange -content $fileContent -regexMatch "\.patch"

if($lastPatchLine -ne -1)
{
    Write-Host File already has PATCHES, inserting ours at $lastPatchLine
    $fileContent[$lastPatchLine-1] += $patchToAdd
    $fileContent | Set-Content $file
}
else
{
    $lastPropertyLine = GetLastOccurange -content $fileContent -regexMatch "HEAD_REF"
    
    Write-Host File has no PATCHES, creating one at $lastPropertyLine
    $fileContent[$lastPropertyLine-1] += "`r`n    PATCHES" + $patchToAdd
    $fileContent | Set-Content $file
}
