#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
cd "${DIR}"

JoyAngVel=1
JoyTransVel=1
IndoorOutdoorRatio=0.7

# Select the Language in the next line 1=English  2=French  3=Spanish  4=German
Language=1

mydate="$(date +%Y-%m-%d)"

printf '\033]0;%s\007' "Virtual House test"

printf '\033[32m%s\033[0m\n' "Welcome to the Virtual House test (Egocentric Mode)"

# Prompt for subject name
printf "Please enter the subject name: "
IFS= read -r patientname

mkdir -p "${patientname}${mydate}_EGO"

./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_1.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 1 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt"
./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_2.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 2 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt" 
./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_3.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 3 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt"
./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_4.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 4 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt"
./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_5.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 5 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt"
./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_6.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 6 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt"
./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_7.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 7 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt"
./build/virtualhouse "${patientname}${mydate}_EGO/${patientname}${mydate}_8.txt" /LANGUAGE ${Language} /INOUTRATIO ${IndoorOutdoorRatio} /JOYTRANSVEL ${JoyTransVel} /JOYANGVEL ${JoyAngVel} /NOINFO /AUTOEXIT /USEJOYSTICK /TRIAL 8 /LOGTOTAL "${patientname}${mydate}_EGO/${patientname}${mydate}_EGO.txt"

