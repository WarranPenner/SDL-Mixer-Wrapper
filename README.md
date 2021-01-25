# SDL_Mixer Wrapper
*Provides a simple wrapper class for SDL_Mixer, allowing audio with SDL2/C++. It is designed to play a small
number of sound effects simultaneously with one music file.*

### How to Use It
* Pointers to `Mix_Music` and `Mix_Chunk` (sound effects) objects are initialized through the `loadMusic`
  function. 
* `Mix_Music` and `Mix_Chunk` objects are not worked with directly, -only pointers are used. These pointers, and
  the `std::string` file paths for their files, are handled by whatever client wants its audio files played.
* When an audio file needs to be played, its pointer is passed through the `playMusic` or `playChunk` functions.
* The class is designed to work with simplistic applications, where a small, limited number of sound effects
  are played at once. If a developer is not concerned about running into problems with too many sound effects,
  the error check and warning in the `playChunk` function should be removed.
