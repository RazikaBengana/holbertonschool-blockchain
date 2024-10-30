<div align="center">
<br>

![Crypto.png](README-image/crypto.png)

</div>


<p align="center">
<img src="https://img.shields.io/badge/-C-yellow">
<img src="https://img.shields.io/badge/-Linux-lightgrey">
<img src="https://img.shields.io/badge/-WSL-brown">
<img src="https://img.shields.io/badge/-Ubuntu%2020.04.4%20LTS-orange">
<img src="https://img.shields.io/badge/-JetBrains-blue">
<img src="https://img.shields.io/badge/-Holberton%20School-red">
<img src="https://img.shields.io/badge/License-not%20specified-brightgreen">
</p>


<h1 align="center"> Blockchain - Crypto </h1>


<h3 align="center">
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#eye-about">About</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#hammer_and_wrench-tasks">Tasks</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#memo-learning-objectives">Learning Objectives</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#computer-requirements">Requirements</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#keyboard-more-info">More Info</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#mag_right-resources">Resources</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#bust_in_silhouette-authors">Authors</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/crypto#octocat-license">License</a>
</h3>

---

<!-- ------------------------------------------------------------------------------------------------- -->

<br>
<br>

## :eye: About

<br>

<div align="center">

**`Blockchain - crypto`** project covers essential cryptographic operations fundamental to blockchain technology, including **key pair generation**, **signing**, and **verification of transactions**.
<br>
The programs implement crucial functions for creating and managing `EC key pairs`, computing **public keys** from **private keys**, signing messages, and verifying signatures using the `secp256k1` elliptic curve.
<br>
<br>
This project has been created by **[Holberton School](https://www.holbertonschool.com/about-holberton)** to enable every student to understand how `cryptographic primitives in blockchain systems` in C language work.

</div>

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :hammer_and_wrench: Tasks

<br>

**`0. SHA256`**

**`1. EC_KEY creation`**

**`2. EC_KEY to public key`**

**`3. EC_KEY from public key`**

**`4. EC_KEY - Save to file`**

**`5. EC_KEY - Load from file`**

**`6. Signature`**

**`7. Signature verification`**

**`8. Library`**

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :memo: Learning Objectives

<br>

**_You are expected to be able to [explain to anyone](https://fs.blog/feynman-learning-technique/), without the help of Google:_**

<br>

```diff

General

+ How a Blockchain is considered “unbreakable”

+ What is a hash algorithm

+ What SHA stands for

+ How hash algorithms apply to Blockchains

+ What is asymmetric cryptography

+ How asymmetric cryptography applies to cryptocurrencies

+ What ECC stands for

+ What ECDSA stands for

+ What a digital signature is

+ How digital signatures apply to cryptocurrencies

```

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :computer: Requirements

<br>

```diff

General

+ Allowed editors: vi, vim, emacs

+ All your files will be compiled on Ubuntu 20.04 LTS

+ Your C programs and functions will be compiled with gcc 9.* using the flags -Wall -Werror -Wextra, -pedantic -Wno-deprecated-declarations and the linker flags -lssl and -lcrypto

+ All your files should end with a new line

+ A README.md file, at the root of the folder of the project, is mandatory

+ Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl

+ The prototypes of all your functions should be included in your header file called crypto/hblk_crypto.h

+ All your header files should be include guarded

```

<br>

**_Why all your files should end with a new line? See [HERE](https://unix.stackexchange.com/questions/18743/whats-the-point-in-adding-a-new-line-to-the-end-of-a-file/18789)_**

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :keyboard: More Info

<br>

### Dependencies:

<br>

- For this project, you will need to [Install the OpenSSL library](https://help.ubuntu.com/community/OpenSSL#Practical_OpenSSL_Usage) (if not already installed).

<br>
<br>

### Data structures:

<br>

- Unless specified otherwise, you are allowed to use the `C` standard library

- You are free to use any data structure that suits you as long as their purpose is well defined

- You are free to print any information on `stderr`, this stream will be discarded during correction. <br>
  Since you are going to use these utility functions in your `Blockchain` project, you are free to manage errors as you wish.

- At the end of this project, the structure of your repository should look like this (you may have additional files):

<br>

```yaml
holbertonschool-blockchain
├── crypto
│   ├── ec_create.c
│   ├── ec_from_pub.c
│   ├── ec_load.c
│   ├── ec_save.c
│   ├── ec_sign.c
│   ├── ec_to_pub.c
│   ├── ec_verify.c
│   ├── hblk_crypto.h
│   ├── libhblk_crypto.a
│   ├── Makefile
│   ├── provided
│   │   └── _print_hex_buffer.c
│   ├── sha256.c
│   └── test
│       ├── ec_create-main.c
│       ├── ec_from_pub-main.c
│       ├── ec_load-main.c
│       ├── ec_save-main.c
│       ├── ec_sign-main.c
│       ├── ec_to_pub-main.c
│       ├── ec_verify-main.c
│       └── sha256-main.c
└── README.md
```

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :mag_right: Resources

<br>

**_Do you need some help?_**

<br>

**Concepts:**

* [[EYNTK] Blockchain - Introduction](https://drive.google.com/file/d/12fVI-oyZkKD03uOXBngYE84-jGIMIOkL/view?usp=sharing)

* [[EYNTK] Blockchain - Crypto](https://drive.google.com/file/d/12kZ1qcEhzMWfSjIe5U3SObfOQpF3blHP/view?usp=sharing)

<br>

**Read or watch:**

* [OpenSSL crypto library](https://www.openssl.org/docs/manmaster/man3/)

* [Provided libraries and sources](https://github.com/hs-hq/holbertonschool-blockchain)

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :bust_in_silhouette: Authors

<br>

<img src="https://img.shields.io/badge/Razika%20Bengana-darkblue" alt="Razika Bengana" width="120">

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :octocat: License

<br>

```Blockchain - crypto``` _project has no license specified._

<br>
<br>

---

<p align="center"><br>2024</p>