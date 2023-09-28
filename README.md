# cudp_demo

A Server/Client demonstation using UDP protocol. In this demo, the Server will echo the message from Client in the reversed direction.

# Getting Started / Installation

This demonstration is written for Linux in C. Make sure that you have neccessary packages installed to compile & install.

```
sudo apt update
```

```
sudo apt install build-essential -y
```

```
sudo apt install make -y
```

Verify package installation:

```
g++ --version
```

```
make -version
```

For server, Monit could help managing the process.

```
sudo apt install monit -y
```

## Server

- Copy everythings in ```src/``` to ```/root/cudp/```
- Build source code

```
cd /root/cudp/
make clean all
```

- Copy ```doc\cudp.cfg``` to ```/etc/monit/conf.d/```
- Reload monit

```
monit reload
```

## Client

Run the following command in source code folder to build:
```
make clean all
```

---
