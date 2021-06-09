import json
import sys
import os


PLAYER_FIELDS = [
    'player_x', 'player_y', 'upgrades'
]

PLATFORM_FIELDS = [
    'visibility', 'sides', 'spriteX', 'spriteY',
    'x', 'y', 'width', 'height',
    'boundsWidth', 'boundsHeight', 'facing'
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
            write_short(binary_file, platform[field])

    end = 0xFF
    binary_file.write(end.to_bytes(1, 'little'))


def load_json_data(filename):
    with open(filename, 'r') as f:
        json_data = json.load(f)
        
    file_prefix = filename.split('.')[0]

    with open(f'../resources/levels/{file_prefix}.bin', 'wb') as f:
        dump_to_bin(json_data, f)


if __name__ == '__main__':
    
    for filename in os.listdir('.'):
        if filename.endswith('.json'):
            load_json_data(filename)
