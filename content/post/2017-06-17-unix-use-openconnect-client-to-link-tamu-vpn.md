---
title: (Unix) Use OpenConnect client to Link TAMU VPN
date: '2017-06-17'
---


OpenConnect is the free software with GNU LGPL v2.1. It's the alternative method to connect to AnyConnect VPN if the user can't use the Cisco VPN client software, or prefer to use the free software. We can get the access for TAMU VPN and connect to the HPRC (High-Performance Research Computer) by the following method.

## 1 Connect to TAMU VPN


Active the TUN module

```
sudo /sbin/modprobe tun
```

Install OpenConnect

```
sudo apt-get install openconnect
```

Connect to VPN by running

```
sudo openconnect connect.tamu.edu
```

After seeing the below message,  
enter the GROUP name: `tunnel_all_traffic`,  
then type the username (netID) and password  

```
POST https://connect.tamu.edu/
Attempting to connect to server 128.194.197.37:443
SSL negotiation with connect.tamu.edu
Connected to HTTPS on connect.tamu.edu
XML POST enabled
Please enter your username and password.
GROUP: [tunnel_all_traffic|tunnel_tamu_traffic]:
```

## 2 Connect to Ada cluster


Open the new terminal and type 

```
ssh <username>@ada.tamu.edu
```

Enter the password to login to Ada cluster

Tip: To stop the VPN connection, simply press `Ctrl+Z` or `Ctrl+C` in the terminal. 

References
===

1. [Openconnect official website](http://www.infradead.org/openconnect/)
2. [How to Connect to Cisco AnyConnect VPN in Ubuntu](http://ubuntuhandbook.org/index.php/2014/11/connect-cisco-anyconnect-vpn-ubuntu/)
3. [Installing and using the OpenConnect client with Debian and Ubuntu for UC Irvine (UCI) VPN](http://www.socsci.uci.edu/~jstern/uci_vpn_ubuntu/ubuntu-openconnect-uci-instructions.html)
3. [Using Cisco AnyConnect VPN with openconnect](https://github.com/dnschneid/crouton/wiki/Using-Cisco-AnyConnect-VPN-with-openconnect)
