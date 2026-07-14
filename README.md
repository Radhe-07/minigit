# MiniGit

MiniGit is a small Git-inspired version control system written in C++17. It is an educational project that recreates a few of Git's core ideas with a simpler storage model: initializing a repository, staging files, creating commits, and walking commit history.

## What It Supports

- `init` creates a `.minigit` repository in the current directory.
- `add <file>` stores a snapshot of a file in the object store and records it in the index.
- `commit -m "message"` creates a commit from the current staged state.
- `log` walks the parent chain and prints commit history.
- `status` prints the active branch and a basic working tree summary.

## How MiniGit Works

MiniGit stores repository data in a local `.minigit` directory:

```text
.minigit/
|-- HEAD
|-- index
|-- next_commit
|-- next_object
|-- commits/
|-- objects/
`-- refs/
    `-- main
```

- `HEAD` points to `refs/main`.
- `objects/` stores full file snapshots created by `add`.
- `index` tracks the latest staged object ID for each file.
- `commits/` stores commit records with an ID, message, parent, and index snapshot.
- `refs/main` stores the latest commit on the only supported branch.
- `next_object` and `next_commit` are simple counters used to generate sequential IDs such as `object1` and `commit1`.

## Build

There is no build system checked into the repository yet, so compile the sources directly with a C++17-compatible compiler.

### g++

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/init.cpp src/status.cpp src/add.cpp src/commit.cpp src/log.cpp -o minigit
```

### MSVC

```powershell
cl /std:c++17 /EHsc /I include src\main.cpp src\init.cpp src\status.cpp src\add.cpp src\commit.cpp src\log.cpp /Fe:minigit.exe
```

## Usage

### Commands

| Command | Description |
| --- | --- |
| `minigit init` | Initialize a new MiniGit repository in the current directory |
| `minigit status` | Show the current branch and a simple file summary |
| `minigit add <filename>` | Stage a file by storing its contents as an object |
| `minigit commit -m "message"` | Create a commit from the current index |
| `minigit log` | Print commit history from newest to oldest |

### Example Workflow

```bash
./minigit init
echo "hello MiniGit" > notes.txt
./minigit add notes.txt
./minigit commit -m "Initial commit"
./minigit log
./minigit status
```

On Windows, use `.\minigit.exe` instead of `./minigit`.

## Project Layout

```text
include/
|-- add.h
|-- commit.h
|-- init.h
|-- log.h
`-- status.h

src/
|-- add.cpp
|-- commit.cpp
|-- init.cpp
|-- log.cpp
|-- main.cpp
`-- status.cpp
```

- `main.cpp` dispatches CLI commands.
- `init.cpp` sets up repository metadata and directories.
- `add.cpp` writes staged file snapshots to the object store.
- `commit.cpp` creates commit records and advances `refs/main`.
- `log.cpp` follows parent commits and prints history.
- `status.cpp` reports a basic working tree view.

## Current Limitations

MiniGit is intentionally minimal and does not aim to be a drop-in replacement for Git.

- Only one branch, `main`, is supported.
- Object IDs and commit IDs are sequential counters, not content hashes.
- `add` stores full file contents; there is no delta storage or compression.
- Commit metadata is minimal: no author, timestamp, or diff view.
- There is no checkout, branching, merging, restore, or remove command yet.
- Status reporting is still basic and does not match Git's full behavior.

## Why This Project Exists

MiniGit is a good project for learning how version control systems work under the hood. It keeps the data model approachable while still demonstrating important concepts such as object storage, staging, commit ancestry, and reference updates.
