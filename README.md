<!--
SPDX-FileCopyrightText: 2024 AFCMS <afcm.contact@gmail.com>
SPDX-License-Identifier: GPL-3.0-or-later
-->

# DevPet

[![PlatformIO CI](https://github.com/AFCMS/devpet/actions/workflows/platformio.yml/badge.svg)](https://github.com/AFCMS/devpet/actions/workflows/platformio.yml)

## Design

```mermaid
flowchart TD
    subgraph graphical_elements[Graphical Elements]
    Node2D -.-> Rect
    Node2D -.-> ProgressBar
    Node2D -.-> SpriteAnimated
    Node2D -.-> SpriteBar
    Node2D -.-> SpriteStatic
    Node2D -.-> TextScrolling
    Node2D -.-> Text
    end

    graphical_elements --> DisplaySystem
    graphical_elements --> DevPetGraphics

    subgraph manager_classes[Manager Classes]
    DevPet --> DevPetGraphics
    DevPetGraphics --> DisplaySystem
    end

    subgraph input[Input]
    Button
    CommSystem
    end

    subgraph body[Body]
    loop
    end

    loop --> DevPet
    Button --> loop
    CommSystem <--> loop

    subgraph hardware[Hardware]
    SSD1306
    serial_port[Serial Port]
    end

    serial_port <--> CommSystem
    DisplaySystem --> SSD1306
```

## Run the project

### Install PlatformIO

The project depends on the [PlatformIO](https://platformio.org) toolkit.

You can either install the [VSCode extension](https://platformio.org/install/ide?install=vscode) or the [CLI](https://platformio.org/install/cli)

### Build

```shell
platformio run
```

### Upload on the ESP32

Make sure the ESP32 is connected to the computer and the USB port is accessible.

```shell
platformio run --target upload
```
