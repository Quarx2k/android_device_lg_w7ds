/*
 * Copyright (C) 2015 The Android Open Source Project, Quarx2k(https://github.com/Quarx2k)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Stubs for libOpenCL.so
int cb_event_notify_egl_sync_is_signaled_qcom() {
    return 0;
}

int cb_event_register_egl_sync_observer_qcom() {
    return 0;
}
#if 0
// Stubs for old sensors.qcom with new QMI
int qmi_client_init_instance() {
   return 0;
}

int qmi_client_register_notify_cb() {
   return 0;
}
#endif
