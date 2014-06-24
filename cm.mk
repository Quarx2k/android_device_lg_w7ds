## Specify phone tech before including full_phone
$(call inherit-product, vendor/cm/config/gsm.mk)

# Release name
PRODUCT_RELEASE_NAME := w7ds

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/lg/w7ds/device_w7ds.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := w7ds
PRODUCT_NAME := cm_w7ds
PRODUCT_BRAND := lg
PRODUCT_MODEL := w7ds
PRODUCT_MANUFACTURER := lg
