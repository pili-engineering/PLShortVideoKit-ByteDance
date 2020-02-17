# -*- coding: utf-8 -*-

import os
import json

print "input root dir:"
rootDir = raw_input()

makeupDir = "ComposeMakeup.bundle/ComposeMakeup"
stickerDir = "StickerResource.bundle/stickers"
filterDir = "FilterResource.bundle/Filter"
makeupListStr = """
{
    "beauty":[
        {
            "path":"beauty_IOS",
            "displayName":"锐化",
            "internalKey":"sharp",
            "intensity":1.0
        },
        {
            "path":"beauty_IOS",
            "displayName":"磨皮",
            "internalKey":"smooth",
            "intensity":1.0
        },
        {
            "path":"beauty_IOS",
            "displayName":"美白",
            "internalKey":"whiten",
            "intensity":1.0
        }
    ],
    "reshape":[
        {
            "path":"reshape",
            "displayName":"瘦脸",
            "internalKey":"Internal_Deform_Overall",
            "intensity":1.0
        },
        {
            "path":"reshape",
            "displayName":"大眼",
            "internalKey":"Internal_Deform_Eye",
            "intensity":1.0
        }
    ]
}
"""

def gen_sticker_list():
    dirpath = os.path.join(rootDir, stickerDir)
    if not os.path.exists(dirpath):
        print "sticker directory not exists!!!"
        return
    listpath = os.path.join(dirpath, "list.json")
    if os.path.exists(listpath):
        return
    json_obj = []
    for sticker in os.listdir(dirpath):
        tmppath = os.path.join(dirpath, sticker)
        if os.path.isdir(tmppath):
            json_obj.append({"path": sticker, "dispalyName": "", "tip": ""})
    file_handle = open(listpath, 'w+')
    file_handle.write(json.dumps(json_obj, indent=4))
    file_handle.close()
    return


def gen_filter_list():
    dirpath = os.path.join(rootDir, filterDir)
    if not os.path.exists(dirpath):
        print "filter directory not exists!!!"
        return
    listpath = os.path.join(dirpath, "list.json")
    if os.path.exists(listpath):
        return
    json_obj = []
    for filter in os.listdir(dirpath):
        tmppath = os.path.join(dirpath, filter)
        if os.path.isdir(tmppath):
            json_obj.append({"path": filter, "dispalyName": "", "intensity": 1.0})
    file_handle = open(listpath, 'w+')
    file_handle.write(json.dumps(json_obj, indent=4))
    file_handle.close()
    return


def gen_makeup_list():
    dirpath = os.path.join(rootDir, makeupDir)
    if not os.path.exists(dirpath):
        print "makeup directory not exists!!!"
        return
    listpath = os.path.join(dirpath, "list_ios.json")
    if os.path.exists(listpath):
        return
    file_handle = open(listpath, 'w+')
    file_handle.write(makeupListStr)
    file_handle.close()
    return


if not os.path.exists(rootDir):
    print "directory not exists!!!"
else:
    gen_sticker_list()
    gen_filter_list()
    gen_makeup_list()