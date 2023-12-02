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

# args handler
parser = argparse.ArgumentParser(description="Clean up script for ApocalypseGame project")
parser.add_argument("-u", "--unreal", help="Options for unreal clean up script", default="")
args = parser.parse_args()

automationFolder = os.path.dirname(__file__)

# search for cleanup scripts and run them
for cleanupScript in os.listdir(automationFolder):
    if cleanupScript.startswith('cleanup-'):
        print('running \'%s\':' % cleanupScript)
        os.system('python %s\\%s %s' % (automationFolder, cleanupScript, args.unreal))
        print('\'%s\' completed.' % cleanupScript)
