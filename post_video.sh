#!/bin/bash

curl --http1.1 -i -X POST -H 'Content-Type: application/json' -d '{"URL" : "https://download.samplelib.com/mp4/sample-5s.mp4" }' localhost:8080/upload
