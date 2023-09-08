#!/bin/bash 

mkdir -p /usr/share/rtc_ds3231

cp clock_init.sh /usr/share/rtc_ds3231
cp rtc-ds3231.service /lib/systemd/system

systemctl enable rtc-ds3231.service
systemctl start rtc-ds3231

