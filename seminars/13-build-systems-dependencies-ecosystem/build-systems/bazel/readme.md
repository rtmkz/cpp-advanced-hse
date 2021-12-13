# Bazel example

* Собираем:
  
  ```shell
  bazel build //clocks:main
  ```

  `//` -- корень репозитория сборки, `clocks` -- пакет (директория с файлом
  `BUILD`), `main` -- таргет.
  
* Запускаем:
  
  ```shell
  bazel-bin/clocks/main
  ```

