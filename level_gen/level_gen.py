import json
import os


PLAYER_FIELDS = [
    'playerX', 'playerY', 'upgrades'
]

PLATFORM_FIELDS = [
    'visibility', 'type', 'sides', 'x', 'y',
    'width', 'height', 'boundsWidth', 'boundsHeight',
    'facing', 'spriteX', 'spriteY'
]


def write_short(f, short_str):
    short_bytes = int(short_str).to_bytes(2, 'little')
    f.write(short_bytes)
    

def dump_to_bin(json_data, binary_file):
    global PLAYER_FIELDS, PLATFORM_FIELDS

    for field in PLAYER_FIELDS:
        write_short(binary_file, json_data[field])

    for platform in json_data['platforms']:
        for field in PLATFORM_FIELDS:
            if field not in platform:
                continue

            write_short(binary_file, platform[field])

    end = 0xFF
    binary_file.write(end.to_bytes(1, 'little'))


def load_json_data(jsonfile):
    with open(jsonfile, 'r') as f:
        json_data = json.load(f)
        
    file_prefix = jsonfile.split('.')[0]

    with open(f'../resources/levels/{file_prefix}.bin', 'wb') as f:
        dump_to_bin(json_data, f)


if __name__ == '__main__':
    for filename in os.listdir('.'):
        if filename.endswith('.json'):
            load_json_data(filename)
