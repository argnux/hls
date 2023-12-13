# HLS service

## Introduction
HLS - HTTP Live Streaming - is a media streaming protocol used to send audio and video over HTTP from an ordinary web server for playback. The technology was developed by Apple Inc. The first release happened in 2009.

The key parts of the HLS service are:
- Server component (encoding media, splitting it into chunks, creating a playlist)
- Distribution component (media files delivery via HTTP)
- Client software (determining the media to request, downloading the media, presenting it to the user)

You can find the detailed information in the [HTTP Live Streaming Specification](https://tools.ietf.org/html/draft-pantos-hls-rfc8216bis).

### Technologies
The server uses
- CMake
- C++
  - Boost.Asio
  - Boost.Beast
  - Boost.Process
- FFmpeg

### Build and start
```sh
./build.sh
./run.sh
```

### Usage examples
Post video:
```sh
curl --http1.1 -i -X POST -H 'Content-Type: application/json' -d '{"URL" : "https://download.samplelib.com/mp4/sample-5s.mp4" }' localhost:8080/upload
```
Clear files
```sh
curl -i -X POST localhost:8080/clean
```

## TODO
  - [ ] Potential errors are wrapped in try-catch
  - [ ] Working CI/CD
  - [ ] Present the video to the user
