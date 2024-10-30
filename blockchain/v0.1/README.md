<div align="center">
<br>

![Data_structures.png](README-image/data_structures.png)

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


<h1 align="center"> Blockchain - Data structures </h1>


<h3 align="center">
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#eye-about">About</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#hammer_and_wrench-tasks">Tasks</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#memo-learning-objectives">Learning Objectives</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#computer-requirements">Requirements</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#keyboard-more-info">More Info</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#mag_right-resources">Resources</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#bust_in_silhouette-authors">Authors</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.1#octocat-license">License</a>
</h3>

---

<!-- ------------------------------------------------------------------------------------------------- -->

<br>
<br>

## :eye: About

<br>

<div align="center">

**`Blockchain - data structures`** project refers to fundamental blockchain components, including **block creation**, **validation**, and **chain management**.
<br>
The programs implement core functionalities such as creating **genesis blocks**, adding new blocks to the chain, verifying block validity, and handling blockchain persistence through **serialization** and **deserialization**.
<br>
<br>
This project has been created by **[Holberton School](https://www.holbertonschool.com/about-holberton)** to enable every student to understand how **basic blockchain data structures** and **operations** in C language work.

</div>

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :hammer_and_wrench: Tasks

<br>

**`0. Create Blockchain`**

**`1. Create Block`**

**`2. Delete Block`**

**`3. Delete Blockchain`**

**`4. Hash Block`**

**`5. Save Blockchain`**

**`6. Load Blockchain`**

**`7. Block validity`**

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :memo: Learning Objectives

<br>

**_You are expected to be able to [explain to anyone](https://fs.blog/feynman-learning-technique/), without the help of Google:_**

<br>

```diff

General

+ How a Blockchain is structured

+ How Blocks refer to each other

+ How immutability is maintained in a Blockchain

+ What is the Genesis Block, and why is it important

+ How to hash a Block, and what information is stored in the hash

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

+ Your C programs and functions will be compiled with gcc 9.4.0 using the flags -Wall -Werror -Wextra, -pedantic -Wno-deprecated-declarations and the linker flags -lssl and -lcrypto

+ All your files should end with a new line

+ A README.md file, at the root of the folder of the project, is mandatory

+ Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl

+ Your library libhblk_crypto.a, located in the crypto folder will be built and linked during correction

+ The prototypes of all your functions should be included in your header file called blockchain/v0.1/blockchain.h

+ All your header files should be include guarded

```

<br>

**_Why all your files should end with a new line? See [HERE](https://unix.stackexchange.com/questions/18743/whats-the-point-in-adding-a-new-line-to-the-end-of-a-file/18789)_**

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :keyboard: More Info

<br>

### Data structures:

<br>

- Please refer to the [concept page linked to this project](https://drive.google.com/file/d/12ryD8hf1c4LfUp2WdoQ6lo35AcQr06NK/view?usp=sharing) to get familiar with the different data structures used in this project.

<br>
<br>

### Additional information:

<br>

- Unless specified otherwise, you are allowed to use the `C` standard library

- You are free to use any data structure that suits you as long as their purpose is well defined

- You are free to print any information on `stderr`, this stream will be discarded during correction. <br>
  Since you are going to use these utility functions in your `Blockchain` project, you are free to manage errors as you wish.

- At the end of this project, the structure of your repository should look like this (you may have additional files):

<br>

```yaml
holbertonschool-blockchain
├── blockchain
│   └── v0.1
│       ├── blockchain_create.c
│       ├── blockchain_deserialize.c
│       ├── blockchain_destroy.c
│       ├── blockchain.h
│       ├── blockchain_serialize.c
│       ├── block_create.c
│       ├── block_destroy.c
│       ├── block_hash.c
│       ├── block_is_valid.c
│       ├── libhblk_blockchain_v0.1.a
│       ├── Makefile
│       ├── provided
│       │   ├── _blockchain_destroy.c
│       │   ├── _blockchain_print.c
│       │   ├── _endianness.c
│       │   ├── endianness.h
│       │   └── _genesis.c
│       └── test
│           ├── blockchain_create-main.c
│           ├── blockchain_deserialize-main.c
│           ├── blockchain_destroy-main.c
│           ├── blockchain_serialize-main.c
│           ├── block_create-main.c
│           ├── block_destroy-main.c
│           ├── block_hash-main.c
│           └── block_is_valid-main.c
├── crypto/
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

* **Everything You Need To Know** - Concept page

* [[EYNTK] Blockchain - Data structures](https://drive.google.com/file/d/12ryD8hf1c4LfUp2WdoQ6lo35AcQr06NK/view?usp=sharing)

<br>

**Read or watch:**

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

```Blockchain - data structures``` _project has no license specified._

<br>
<br>

---

<p align="center"><br>2024</p>