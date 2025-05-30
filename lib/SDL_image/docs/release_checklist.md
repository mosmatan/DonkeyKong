# Release checklist

* Run `build-scripts/create-release.py -R libsdl-org/SDL_image --ref <branch>` to do
  a dry run creating the release assets. Verify that the archives are correct.

* Tag the release, e.g. `git tag release-3.8.0; git push --tags`

* Run `build-scripts/create-release.py -R libsdl-org/SDL_image --ref <release-tag>`
  to have GitHub Actions create release assets. This makes sure the revision
  string baked into the archives is correct.

## New feature release

* Update `CHANGES.txt`

* Bump version number to 3.EVEN.0 in all these locations:

    * `include/SDL3_image/SDL_image.h`:
        `SDL_IMAGE_MAJOR_VERSION`, `SDL_IMAGE_MINOR_VERSION`, `SDL_IMAGE_MICRO_VERSION`
    * `CMakeLists.txt`:
        `MAJOR_VERSION`, `MINOR_VERSION`, `MICRO_VERSION`
    * `src/version.rc`:
        `FILEVERSION`, `PRODUCTVERSION`, `FileVersion`, `ProductVersion`
    * `VisualC/Version.rc`:
        `FILEVERSION`, `PRODUCTVERSION`, `FileVersion`, `ProductVersion`
    * `Xcode/Info-Framework.plist`:
        `CFBundleShortVersionString`, `CFBundleVersion`

* Bump ABI version information

    * `Xcode/SDL_image.xcodeproj/project.pbxproj`:
        `DYLIB_CURRENT_VERSION`, `DYLIB_COMPATIBILITY_VERSION`
        * set first number in `DYLIB_CURRENT_VERSION` to
            (100 * *minor*) + 1
        * set second number in `DYLIB_CURRENT_VERSION` to 0
        * set `DYLIB_COMPATIBILITY_VERSION` to the same value

* Run `./build-scripts/test-versioning.sh` to verify that everything is consistent

* Do the release

## New bugfix release

* Check that no new API/ABI was added

    * If it was, do a new feature release (see above) instead

* Bump version number from 3.Y.Z to 3.Y.(Z+1) (Y is even)

    * Same places as listed above

* Bump ABI version information

    * `Xcode/SDL_image.xcodeproj/project.pbxproj`:
        `DYLIB_CURRENT_VERSION`, `DYLIB_COMPATIBILITY_VERSION`
        * set second number in `DYLIB_CURRENT_VERSION` to *patchlevel*
        * Leave `DYLIB_COMPATIBILITY_VERSION` unchanged

* Run `./build-scripts/test-versioning.sh` to verify that everything is consistent

* Do the release

## After a feature release

* Create a branch like `release-3.6.x`

* Bump version number to 3.ODD.0 for next development branch

    * Same places as listed above

* Bump ABI version information

    * Same places as listed above
    * Assume that the next feature release will contain new API/ABI

* Run `./build-scripts/test-versioning.sh` to verify that everything is consistent

* Add a new milestone for issues

## New development prerelease

* Bump version number from 3.Y.Z to 3.Y.(Z+1) (Y is odd)

    * Same places as listed above

* Bump ABI version information

    * `Xcode/SDL_image.xcodeproj/project.pbxproj`:
        `DYLIB_CURRENT_VERSION`, `DYLIB_COMPATIBILITY_VERSION`
        * set first number in `DYLIB_CURRENT_VERSION` to
            (100 * *minor*) + *patchlevel* + 1
        * set second number in `DYLIB_CURRENT_VERSION` to 0
        * set `DYLIB_COMPATIBILITY_VERSION` to the same value

* Run `./build-scripts/test-versioning.sh` to verify that everything is consistent

* Do the release
