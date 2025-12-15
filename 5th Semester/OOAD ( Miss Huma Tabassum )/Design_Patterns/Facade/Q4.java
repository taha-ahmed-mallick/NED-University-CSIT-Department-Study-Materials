public class FacadePatternExample {
    public static void main(String[] args) {
        VideoConverter converter = new VideoConverter();
        
        // Convert videos using the simple facade interface
        converter.convertVideo("my_video", "mp4");
        converter.convertVideo("presentation", "ogg");
        converter.convertVideo("tutorial", "mp4");
    }
}

// Subsystem classes 
class VideoFile {
    public void load(String filename) {
        System.out.println("Loading video file: " + filename);
    }
    
    public void save(String filename) {
        System.out.println("Saving video file: " + filename);
    }
}

class AudioMixer {
    public void extractAudio(String filename) {
        System.out.println("Extracting audio from: " + filename);
    }
    
    public void mixAudio(String filename) {
        System.out.println("Mixing audio for: " + filename);
    }
}

class BitrateReader {
    public void read(String filename) {
        System.out.println("Reading bitrate for: " + filename);
    }
    
    public void convert(String filename, String format) {
        System.out.println("Converting bitrate to " + format + " format");
    }
}

class CodecFactory {
    public void getCodec(String format) {
        System.out.println("Getting codec for: " + format);
    }
}

class OggCompressionCodec {
    public void compress() {
        System.out.println("Compressing using Ogg codec");
    }
}

class MPEG4CompressionCodec {
    public void compress() {
        System.out.println("Compressing using MPEG4 codec");
    }
}

// Facade Class 
class VideoConverter {
    private VideoFile videoFile = new VideoFile();
    private AudioMixer audioMixer = new AudioMixer();
    private BitrateReader bitrateReader = new BitrateReader();
    private CodecFactory codecFactory = new CodecFactory();
    private OggCompressionCodec oggCodec = new OggCompressionCodec();
    private MPEG4CompressionCodec mpeg4Codec = new MPEG4CompressionCodec();
    
    public void convertVideo(String filename, String format) {
        System.out.println("Starting video conversion process...");
        
        // Step 1: Load the video file
        videoFile.load(filename);
        
        // Step 2: Extract and process audio
        audioMixer.extractAudio(filename);
        audioMixer.mixAudio(filename);
        
        // Step 3: Read and convert bitrate
        bitrateReader.read(filename);
        bitrateReader.convert(filename, format);
        
        // Step 4: Get appropriate codec
        codecFactory.getCodec(format);
        
        // Step 5: Compress using the selected codec
        if ("ogg".equalsIgnoreCase(format)) {
            oggCodec.compress();
        } else if ("mp4".equalsIgnoreCase(format)) {
            mpeg4Codec.compress();
        }
        
        // Step 6: Save the converted file
        videoFile.save(filename + "." + format);
        
        System.out.println("Video conversion completed successfully!");
        System.out.println("Output: " + filename + "." + format + "\n");
    }
}