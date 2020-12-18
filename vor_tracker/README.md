# VOR Tracker

A VOR station scanning, tracking, and localization module.

VOR Tracking is based on [vortrack](https://github.com/TLeconte/vortrack).

## Dependencies

```
$ sudo apt update
$ sudo apt install librtlsdr
```

## Build

For rtl sdr :
```
$ make
```

## Usage

> vortracker [-g gain] [-l interval ] [-r device] frequency (in Mhz)

 -l interval : interval in second between two measurements

 -g gain in tens of db (ie : -g 400 ) 

 -p ppm :  ppm freq shift

 -r n : rtl device number (mandatory for rtl sdr)

## Example

```
$ ./vortracker -g 0 144.00
```