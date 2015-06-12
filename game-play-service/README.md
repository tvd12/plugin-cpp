Setup

- From your cocos2d-x project, create folder named ‘libraries’
- Copy google-play-service into libraries

1. Setup on Xcode - ios

Step 1. Install CocoaPods
	- link: http://cocoapods.org/
Step 2. Move to your_project_path/proj.ios_mac and run command: pod init
Step 3. Fill Podfile

platform :ios, '7.0'
pod 'GooglePlayGames'

pod_target = "Pods"

post_install do |installer|
    # HEADER_SEARCH_PATHS add to $(inherited)
    installer.project.build_configurations.each do |configuration|
        workDir = Dir.pwd
        xcconfigFilename = "#{workDir}/Pods/Target\ Support\ Files/#{pod_target}/#{pod_target}.#{configuration.name}.xcconfig"
        xcconfig = File.read(xcconfigFilename)
        newXcconfig = xcconfig.gsub(/HEADER_SEARCH_PATHS = "/, "HEADER_SEARCH_PATHS = $(inherited) \"")
        File.open(xcconfigFilename, "w") { |file| file << newXcconfig }
    end
end 

Step 4. Run command pod install

Step 6. Close your project on XCode and open your_project.xcworkspace

Step 7. Right click on your project on Xcode and select Add Files To “your project” and add google-play-service

Step 8.

2. Setup on Eclipse - android

Step 1. Import google-play-service into eclipse

Step 2. Add google-play-service lib into your android project

Step 3. Import android-support-v7-appcompat into eclipse (from SDK_ROOT/extras/android/support/v7/appcompat)

Step 4. Import google_play_services-lib into eclipse (from SDK_ROOT/extras/google/google_play_services/libproject)

Step 5. Add google_play_services-lib and android-support-v7-appcompat into google-play-service

Step 6. 
