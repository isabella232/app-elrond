# Elrond App for the Ledger Nano S

[![Build Status](https://travis-ci.com/ElrondNetwork/ledger-elrond.svg?branch=master)](https://travis-ci.com/ElrondNetwork/ledger-elrond)

## Introduction

This is the official Elrond wallet app for the [Ledger Nano S](https://www.ledgerwallet.com/products/ledger-nano-s).

## Prerequisites

### Latest firmware

Before proceeding with the installation, please make sure your device is up-to-date with the latest firmware.

### Connectivity

Furthermore, you need to configure your OS to enable the connectivity with the Nano S device. For example, on Linux, you have to issue the following command:

```
wget https://raw.githubusercontent.com/LedgerHQ/udev-rules/master/add_udev_rules.sh | sudo bash
```

For other platforms, please have a look on [this article](https://support.ledger.com/hc/en-us/articles/115005165269) from ledger.com.

### Python package `ledgerblue`

```
pip3 install --user --upgrade --no-cache-dir ledgerblue
```

Note that `python3` and `pip3` are required in order to install `ledgerblue`.


## Installation

Download the latest `*.hex` file from our [releases page](https://github.com/ElrondNetwork/ledger-elrond/releases). If `wget` is available on your machine, then:

```
export APP_VERSION=1.0.8

wget https://github.com/ElrondNetwork/ledger-elrond/releases/download/v${APP_VERSION}/elrond-ledger-app-v${APP_VERSION}.hex
```

Now that you've downloaded the app and `ledgerblue` package is available, let's load the app on the device:

```
export APP_VERSION=1.0.8

python3 -m ledgerblue.loadApp --curve ed25519 --path "44'/508'" --appFlags 0x240 --tlv --targetId 0x31100004 --targetVersion=1.6.0 --delete --appName Elrond --appVersion ${APP_VERSION} --fileName elrond-ledger-app-v${APP_VERSION}.hex --dataSize 64 --icon "010000000000ffffffffffffffffff37ecdffbeff7f7eff7eff7eff7efeff7dffb37ecffffffffffff"
```

To remove the app from the device, issue the following command:

```
python3 -m ledgerblue.deleteApp --targetId 0x31100004 --appName Elrond
```

## Testing

The `testApp` folder contains a sample *Go* application to prepare Elrond transactions, which you can sign using the Ledger device. The signed transactions are then dispatched to the [Elrond Proxy](https://api.elrond.com), in order to be processed and saved on the blockchain.

Download the latest `ElrondTestApp*` file from our [releases page](https://github.com/ElrondNetwork/ledger-elrond/releases). Linux, MacOS and Windows are supported. Then execute the file while the device is connected to your computer. You will be requested to enter transaction details and then continue with the signing step.

Before running the application, you need to mark it as executable on Linux / MacOS:

```
chmod +x ./ElrondTestApp*
```

Also please note that on Windows you might receive the _Unknown publisher_ warning from the [UAC facility](https://en.wikipedia.org/wiki/User_Account_Control) when you first run the _testApp_.

## Development environment: building and installing

To build locally, you must first clone this repository, then set up the development environment:

```$ source prepare-devenv s```

This could take a while. Then, load the app as follows:

```$ make load```

To remove the app from the device, run:

```$ make delete```
