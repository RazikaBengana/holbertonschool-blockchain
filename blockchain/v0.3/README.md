<div align="center">
<br>

![Transactions.png](README-image/transactions.png)

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


<h1 align="center"> Blockchain - Transactions </h1>


<h3 align="center">
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#eye-about">About</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#hammer_and_wrench-tasks">Tasks</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#memo-learning-objectives">Learning Objectives</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#computer-requirements">Requirements</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#keyboard-more-info">More Info</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#mag_right-resources">Resources</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#bust_in_silhouette-authors">Authors</a> •
<a href="https://github.com/RazikaBengana/holbertonschool-blockchain/tree/main/blockchain/v0.3#octocat-license">License</a>
</h3>

---

<!-- ------------------------------------------------------------------------------------------------- -->

<br>
<br>

## :eye: About

<br>

<div align="center">

**`Blockchain - transactions`** project covers the **implementation of cryptocurrency transactions**, including **creation**, **validation**, and **integration** into the blockchain structure.
<br>
The programs handle transaction signing, verification of digital signatures, management of unspent transaction outputs (`UTXOs`), and the incorporation of multiple transactions into blocks during the mining process.
<br>
<br>
This project has been created by **[Holberton School](https://www.holbertonschool.com/about-holberton)** to enable every student to understand how **cryptocurrency transactions and their integration into a blockchain** in C language work.

</div>

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :hammer_and_wrench: Tasks

<br>

**`0. Create transaction output`**

**`1. Create unspent transaction output`**

**`2. Create transaction input`**

**`3. Transaction ID`**

**`4. Sign transaction input`**

**`5. Create transaction`**

**`6. Transaction validation`**

**`7. Coinbase transaction`**

**`8. Coinbase transaction validation`**

**`9. Delete transaction`**

**`10. Update Blockchain and Block creation/deletion`**

**`11. Create/delete list of unspent`**

**`12. Update: Hash Block`**

**`13. Update: Block validation`**

**`14. Update all unspent`**

**`15. Update: Blockchain serialization & deserialization`**

**`16. Blockchain library`**

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :memo: Learning Objectives

<br>

**_You are expected to be able to [explain to anyone](https://fs.blog/feynman-learning-technique/), without the help of Google:_**

<br>

```diff

General

+ How to build a transaction

+ What is a transaction input

+ What is a transaction output

+ Why to sign a transaction input

+ How to compute the balance of given wallet

+ What is a coinbase transaction and why it is used

+ How to ensure immutability of a transaction

+ What is the difference between the UTXO and the Account-based transaction models

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

+ Your C programs and functions will be compiled with gcc 9.* using the flags -Wall -Werror -Wextra, -pedantic and the linker flags -lssl and -lcrypto

+ Your library libhblk_crypto.a, located in the crypto folder will be built and linked during correction

+ All your files should end with a new line

+ A README.md file, at the root of the folder of the project, is mandatory

+ Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl

+ The prototypes of all your functions should be included in your header file called blockchain/v0.3/blockchain.h

+ All your header files should be include guarded

```

<br>

**_Why all your files should end with a new line? See [HERE](https://unix.stackexchange.com/questions/18743/whats-the-point-in-adding-a-new-line-to-the-end-of-a-file/18789)_**

<br>
<br>

<!-- ------------------------------------------------------------------------------------------------- -->

## :keyboard: More Info

<br>

### Prerequisites:

<br>

- Create the folder `blockchain/v0.3/` and copy the following files in it:

    - `blockchain/v0.2/blockchain_create.c`
    - `blockchain/v0.2/blockchain_deserialize.c`
    - `blockchain/v0.2/blockchain_destroy.c`
    - `blockchain/v0.2/blockchain.h`
    - `blockchain/v0.2/blockchain_serialize.c`
    - `blockchain/v0.2/block_create.c`
    - `blockchain/v0.2/block_destroy.c`
    - `blockchain/v0.2/block_hash.c`
    - `blockchain/v0.2/block_is_valid.c`

- Modify your code so when a Blockchain is serialized, the version stored is `0.3`

<br>
<br>

### Data structures:

<br>

- Please refer to the [concept page linked to this project](https://drive.google.com/file/d/12vUgo-DBU0N5-7D8VeP4yHWvMiICIJ0W/view?usp=sharing).
  Don’t forget to update the **Blockchain** and **Block data structures**.

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
│   ├── v0.1/
│   ├── v0.2/
│   └── v0.3
│       ├── blockchain_create.c
│       ├── blockchain_deserialize.c
│       ├── blockchain_destroy.c
│       ├── blockchain_difficulty.c
│       ├── blockchain.h
│       ├── blockchain_serialize.c
│       ├── block_create.c
│       ├── block_destroy.c
│       ├── block_hash.c
│       ├── block_is_valid.c
│       ├── block_mine.c
│       ├── hash_matches_difficulty.c
│       ├── libhblk_blockchain_v0.3.a
│       ├── Makefile
│       ├── provided
│       │   ├── _blockchain_print.c
│       │   ├── _endianness.c
│       │   ├── endianness.h
│       │   ├── _genesis.c
│       │   ├── _print_hex_buffer.c
│       │   └── _transaction_print.c
│       ├── test
│       │   ├── blockchain_create-main.c
│       │   ├── blockchain_deserialize-main.c
│       │   ├── blockchain_destroy-main.c
│       │   ├── blockchain_difficulty-main.c
│       │   ├── blockchain_serialize-main.c
│       │   ├── block_create-main.c
│       │   ├── block_destroy-main.c
│       │   ├── block_hash-main.c
│       │   ├── block_is_valid-main.c
│       │   ├── block_mine-main.c
│       │   └── hash_matches_difficulty-main.c
│       └── transaction
│           ├── coinbase_create.c
│           ├── coinbase_is_valid.c
│           ├── test
│           │   ├── coinbase_create-main.c
│           │   ├── coinbase_is_valid-main.c
│           │   ├── transaction_create-main.c
│           │   ├── transaction_destroy-main.c
│           │   ├── transaction_hash-main.c
│           │   ├── transaction_is_valid-main.c
│           │   ├── tx_in_create-main.c
│           │   ├── tx_in_sign-main.c
│           │   ├── tx_out_create-main.c
│           │   ├── unspent_tx_out_create-main.c
│           │   └── update_unspent-main.c
│           ├── transaction_create.c
│           ├── transaction_destroy.c
│           ├── transaction.h
│           ├── transaction_hash.c
│           ├── transaction_is_valid.c
│           ├── tx_in_create.c
│           ├── tx_in_sign.c
│           ├── tx_out_create.c
│           ├── unspent_tx_out_create.c
│           └── update_unspent.c
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

* EYNTK - Transactions

* [[EYNTK] Blockchain - Transactions](https://drive.google.com/file/d/12vUgo-DBU0N5-7D8VeP4yHWvMiICIJ0W/view?usp=sharing)

<br>

**Read or watch:**

* [How a Bitcoin transaction works, CNN](https://www.ccn.com/ex-bitcoin-skeptic-ron-paul-says-crypto-could-prevent-recession/)

* [UTXO vs Account-based transaction model](https://blockonomi.com/utxo-vs-account-based-transaction-models/)

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

```Blockchain - transactions``` _project has no license specified._

<br>
<br>

---

<p align="center"><br>2024</p>