#!/bin/sh

# Bootstrapping steps. Here we create needed directories on the guest
mkdir -p ~/.ssh
mkdir -p ~/.ansible
mkdir -p ~/.config
mkdir -p ~/.config/openstack

# Commands installing required packages
apt-get update
apt install python3-pip
pip3 install --upgrade ansible
python3 -m pip install --upgrade pip setuptools wheel
python3 -m pip install --upgrade openstacksdk
ansible-galaxy collection install openstack.cloud
pip install kafka-python