/*
* Copyright (C) 2012 The CyanogenMod Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

package com.android.internal.telephony;

import static com.android.internal.telephony.RILConstants.*;

import android.content.Context;
import android.os.AsyncResult;
import android.os.Message;


public class LgeRIL extends RIL implements CommandsInterface {
	public LgeRIL(Context context, int networkMode, int cdmaSubscription, Integer instanceId) {
		super(context, networkMode, cdmaSubscription, instanceId);
		
		mQANElements = 5;
	}

	@Override
	public void
	setNetworkSelectionModeManual(String operatorNumeric, Message response) {
		RILRequest rr
			= RILRequest.obtain(RIL_REQUEST_SET_NETWORK_SELECTION_MANUAL,
				response);

		if (RILJ_LOGD) riljLog(rr.serialString() + "> " + requestToString(rr.mRequest)
			+ " " + operatorNumeric);

		rr.mParcel.writeInt(2);
		rr.mParcel.writeString(operatorNumeric);
		rr.mParcel.writeString("NOCHANGE");

		send(rr);
	}

}
