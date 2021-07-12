#!/bin/bash
python3 wiki/make_all_img_page.py
git add wiki
git commit -m "auto update wiki/md"