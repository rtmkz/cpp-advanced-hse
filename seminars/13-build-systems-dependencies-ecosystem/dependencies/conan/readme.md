# Woodpecker

Logging library (not really).

## Requirements

- Conan

Installation:

```shell
pipenv shell
pipenv install
```

## Dependencies

- fmt
- date

Installation:
```shell
mkdir build && cd build
conan install ..
```

## Examples

Build and run example (in `build` directory):
```shell
cmake ..
make example && bin/example $USER
```
