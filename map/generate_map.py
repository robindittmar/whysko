import json
import random


def fully_random():
    tiles = []
    for x in range(64):
        for y in range(64):
            tiles.append({
                'x0': x * 64,
                'y0': y * 64,
                'x1': (x + 1) * 64,
                'y1': (y + 1) * 64,
                'texture': random.choice(
                    ["floor", "wall_right", "wall_left", "wall_bottom", "wall_top", "table", "chair", "mixer"])
            })

    with open('tiles.generated.json', 'w') as f:
        f.write(json.dumps(tiles))


def simple_structured():
    tiles = []
    for x in range(64):
        for y in range(64):
            if x == 0:
                texture = 'wall_left'
            elif x == 63:
                texture = 'wall_right'
            elif y == 0:
                texture = 'wall_top'
            elif y == 63:
                texture = 'wall_bottom'
            elif x == 15 and y == 23:
                texture = 'mixer'
            else:
                texture = 'floor'

            tiles.append({
                'x0': x * 64,
                'y0': y * 64,
                'x1': (x + 1) * 64,
                'y1': (y + 1) * 64,
                'texture': texture
            })

        with open('tiles.generated.json', 'w') as f:
            f.write(json.dumps(tiles))


def main():
    # fully_random()
    simple_structured()


if __name__ == '__main__':
    main()
