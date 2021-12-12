# Dependencies via vcpkg example

## Зависимости

Почему-то `vcpkg` не додумался до специального файла, в котором можно
указать все необходимые зависимости с их версиями, поэтому ставим так:

```shell
vcpkg install imgui
vcpkg install glfw3
vcpkg install glew
```

## Сборка

```shell
mkdir build && cd build
export VCPKG_ROOT=<FILL ME>
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
make main
```

## Запуск

```shell
./main
```

## Откуда код?

[Отсюда](https://github.com/conan-io/examples/tree/master/libraries/dear-imgui/basic).
