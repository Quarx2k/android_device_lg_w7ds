#!/system/bin/sh

model=`getprop ro.product.model`

mount -o remount,rw /system
rm /system/usr/keylayout/Generic.kl

if [ "$model" = "LG-D410" ] || [ "$model" = "LG-D410hn" ]; then
	ln -s /system/usr/keylayout/Generic-D410.kl /system/usr/keylayout/Generic.kl
else
	ln -s /system/usr/keylayout/Generic-D4x5.kl /system/usr/keylayout/Generic.kl
fi

if [ "$model" = "LG-D410" ] || [ "$model" = "LG-D405" ]; then
	chmod 000 /system/etc/permissions/android.hardware.nfc.xml
	chmod 000 /system/etc/permissions/android.hardware.nfc.hce.xml
	chmod 000 /system/lib/hw/nfc_nci.w7.so
	chmod 000 /system/app/NfcNci/NfcNci.apk
fi

mount -o remount,ro /system
