source: tree/development/include/error/error.hpp
source: tree/development/source/error/error.cpp

!!! warning
    This project is still in its early version and is under constant
    development. Expect the documentation to change frequently.

# `aequus::error::` #

The error namespace is used to define and handle SDL error that may arise
durring the program run time. It provides functions that will retreave the
error, and automaticaly enter it into the log, or if desired the developer can
request the error string directly, and utilize it as desired.

## Summary ##

---

### [Functions](#functions_1) ###

|               | Function                                                                      |
|---------------|-------------------------------------------------------------------------------|
| `void`        | [`LogSdlError()`](#logsdlerror)<br> Logs the latest SDL error to Pessum       |
| `void`        | [`LogImgError()`](#logimgerror)<br> Logs the latest SDL_image error to Pessum |
| `void`        | [`LogTtfError()`](#logttferror)<br> Logs the latest SDL_ttf error to Pessum   |
| `void`        | [`LogMixError()`](#logmixerror)<br> Logs the latest SDL_mixer error to Pessum |
| `std::string` | [`GetSdlError()`](#getsdlerror)<br> Gets the latest SDL error                 |
| `std::string` | [`GetImgError()`](#getimgerror)<br> Gets the latest SDL_image error           |
| `std::string` | [`GetTtfError()`](#getttferror)<br> Gets the latest SDL_ttf error             |
| `std::string` | [`GetMixError()`](#getmixerror)<br> Gets the latest SDL_mixer error           |

## Functions ##

---

### `LogSdlError` ###

Logs the latest SDL error to Pessum.

```cpp
void aequus::error::LogSdlError();
```
This function retraves the latest SDL error, and logs that into the Pessum
error handeling of the project, with a type of `pessum::ERROR`.

### `LogImgError` ###

Logs the latest SDL_image error to Pessum.

```cpp
void aequus::error::LogImgError();
```

This function retreaves the latest SDL_image error, and logs that into the
Pessum error handeling of the project, with a type of `pessum::ERROR`.

### `LogTtfError` ###

Logs the latest SDL_ttf error to Pessum

```cpp
void aequus::error::LogTtfError();
```

This function retreves the latest SDL_ttf error, and logs that into the Pessum
error handeling of the project, with a type of `pessum::ERROR`.

### `LogMixError` ###

Logs the latest SDL_mix error to Pessum

```cpp
void aequus::error::LogMixError();
```

This function retreves the latest SDL_mixer error, and logs that into the
Pessum error handleing of the project, with a type of `pessum::ERROR`.

### `GetSdlError` ###

Get that latest SDL error

```cpp
std::string aequus::error::GetSdlError();
```

This function retreves the latest SDL error, and returns the string
representation.

**Returns:** `std::string` representing the SDL error.

### `GetImgError` ###

Get that latest SDL_image error

```cpp
std::string aequus::error::GetImgError();
```

This function retreves the latest SDL_image error, and returns the string
representation.

**Returns:** `std::string` representing the SDL_image error.

### `GetTtfError` ###

Get that latest SDL_ttf error

```cpp
std::string aequus::error::GetTtfError();
```

This function retreves the latest SDL_ttf error, and returns the string
representation.

**Returns:** `std::string` representing the SDL_ttf error.

### `GetMixError` ###

Get that latest SDL_mixer error

```cpp
std::string aequus::error::GetMixError();
```

This function retreves the latest SDL_mixer error, and returns the string
representation.

**Returns:** `std::string` representing the SDL_mixer error.

