# HLS service

## Introduction
HLS - HTTP Live Streaming - is a media streaming protocol used to send audio and video over HTTP from an ordinary web server for playback. The technology was developed by Apple Inc. The first release happened in 2009.

The key parts of the HLS service are:
- Server component (encoding media, splitting it into chunks, creating a playlist)
- Distribution component (media files delivery via HTTP)
- Client software (determining the media to request, downloading the media, presenting it to the user)

You can find the detailed information in the [HTTP Live Streaming Specification](https://tools.ietf.org/html/draft-pantos-hls-rfc8216bis).

## Task
1. Create a `HOWTO.md` file describing the use case for your solution (how to build, run, post video, clean up generated files)
2. Create a server which:
   1. Named hls-service
      - The server must have a default port of 8080
   3. Receives a `.mp4` file via HTTP and sends the link to the created [playlist](https://tools.ietf.org/html/draft-pantos-hls-rfc8216bis-08#section-4) as a response/
      - Endpoint path to upload the video must be called `/upload`
   4. Splits the file into smaller chunks of equal length (files with `.ts` extension). You should use H.264 codec for video and AAC for audio to create a chunk
   5. Composes a [playlist](https://tools.ietf.org/html/draft-pantos-hls-rfc8216bis-08#section-4). The playlist must have a `.m3u8` file extension. For better understanding, take a look at the [playlist examples](https://tools.ietf.org/html/draft-pantos-hls-rfc8216bis-08#section-8)
   6. Serves the playlist along with the media chunks, making it accessible to the clients
   7. Provides an endpoint path to clean saved and generated files `/clean`
3. Test your solution
   - You can use [VLC Player](https://www.videolan.org/vlc/index.html), or browser extension [Native HLS](https://www.google.com/search?q=Native+HLS), or any other player with HLS support
   - Make sure your solution satisfies the checks [##Maintainer](##Maintainer)
4. Upload your solution into `hls-service` folder of your private repository, and create a MR

### Important notices
- Use [FFmpeg](https://ffmpeg.org/) for steps 2.3 and 2.4 implementations
- Forbidden to edit:
  - `README.md`
  - `post_video.sh`
  - `clean_files.sh`
  - `build.sh`
- Allow to edit:
  - `run.sh`

### Technologies
The server must be written in
- C++
  - Required:
    - CMake
    - Boost.Asio
  - Recommended:
    - FFmpeg
    - Boost.Beast
    - Boost.Process

### Usage examples
Post video:
```sh
curl -i -X POST -H 'Content-Type: application/json' -d '{"URL" : "https://download.samplelib.com/mp4/sample-5s.mp4" }' localhost:8080/upload
```
Clear files
```sh
curl -i -X POST localhost:8080/clean
```

## Maintainer

- Preconditions
    - [x] Files not changed:
      - [x] `README.md`
      - [x] `post_video.sh`
      - [x] `clean_files.sh`
      - [x] `build.sh`
    - [ ] There is a file `HOWTO.md` describing the use case of the solution
    - [x] Install ffmpeg

- Runtime
    - [x] Build project using `./build.sh`
    - [x] Run service using `./run.sh`
    - [x] Send request using `./post_video.sh`
      - [x] The `.mp4` file has been successfully uploaded via HTTP to the `/upload` endpoint
      - [x] The server sends in response a link to the created playlist after uploading the file
    - [x] The chunks (files with `.ts` extension) and playlist (files with `.m3u8` extension) appear in the file system directory
    - [x] It is possible to watch the video of the received link using an HLS-enabled player
    - [x] Send clean request using `./clean_files.sh`
      - [x] Clean up saved and generated files in the file system directory
- Code
    - [x] Used CMake
    - [x] Used boost::asio
    - [x] Header guards are present
    - [x] No raw pointers used and no potential memory leaks exist
    - [ ] Potential errors are wrapped in try-catch
