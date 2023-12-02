# Copyright (C) 2023 Iran555 iran555@proton.me
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#         http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import argparse
import os
import shutil

# args handler
parser = argparse.ArgumentParser(description = "Clean up script for unreal part of ApocalypseGame project")
parser.add_argument("-f", "--folders", help="Also remove temp folders", action='store_const', default='NULL')
args = parser.parse_args()

unrealFolder = '%s\\%s' % (os.path.dirname(__file__), "..\\unreal\\")

if not args.folders == 'NULL':
    print('removing temp folder...')
    shutil.rmtree('%s%s' % (unrealFolder, ".idea"),               ignore_errors=True)
    shutil.rmtree('%s%s' % (unrealFolder, "Binaries"),            ignore_errors=True)
    shutil.rmtree('%s%s' % (unrealFolder, "Build"),               ignore_errors=True)
    shutil.rmtree('%s%s' % (unrealFolder, "Saved"),               ignore_errors=True)
    shutil.rmtree('%s%s' % (unrealFolder, "Intermediate"),        ignore_errors=True)
    shutil.rmtree('%s%s' % (unrealFolder, "DerivedDataCache"),    ignore_errors=True)

print('fixing format of "UPROJECT"...')
uproject = open('%s%s' % (unrealFolder, "ApocalypseGame.uproject"), "r")
workingSection = False; ignoreNextBracket = False; workingObject = False
newFile = ''
for line in uproject:
    if '[' in line:
        if not workingSection:
            workingSection = True
            newFile += line
            continue
        else:
            ignoreNextBracket = True
    if not workingSection:
        newFile += line
        continue
    if ']' in line:
        if ignoreNextBracket:
            ignoreNextBracket = False
        else:
            workingSection = False
            newFile += line
            continue

    if '{' in line and not workingObject:
        # this script has been run once
        if '"Name"' in line:
            newFile += line
        else:
            newFile += '\t\t{ '
            workingObject = True
        continue
    if workingObject and '}' in line:
        workingObject = False
        newFile += ' },\n'
        continue

    line = line.replace('\n', '').replace('  ', '').replace('\t', '')
    newFile += line

newFile = newFile.replace(',\n\t]', '\n\t]')
if not newFile.endswith('\n'): newFile += '\n'

uproject.close()
uproject = open(unrealFolder + "ApocalypseGame.uproject", "w")
uproject.write(newFile)
