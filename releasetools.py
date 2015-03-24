# Copyright (C) 2012 The Android Open Source Project
# Copyright (C) 2014 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os

TARGET_DIR = os.getenv('OUT')

def FullOTA_InstallEnd(self):
  self.output_zip.write(os.path.join(TARGET_DIR, "fixup.sh"), "fixup.sh")
  self.script.AppendExtra('package_extract_file("fixup.sh", "/tmp/fixup.sh");')
  self.script.AppendExtra('set_metadata("/tmp/fixup.sh", "uid", 0, "gid", 0, "mode", 0755);')
  self.script.Mount("/system")
  self.script.AppendExtra('run_program("/tmp/fixup.sh");')
  self.script.Unmount("/system");
