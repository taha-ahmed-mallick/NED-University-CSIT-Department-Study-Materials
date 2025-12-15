public class DataMiningApp {

    public static void main(String[] args) {

        DataMining docMiner = new DocDataMiner();
        docMiner.mineData("document.doc");

        DataMining csvMiner = new CSVDataMiner();
        csvMiner.mineData("data.csv");

        DataMining pdfMiner = new PDFDataMiner();
        pdfMiner.mineData("report.pdf");
    }
}


abstract class DataMining {

    // Template method
    public final void mineData(String path) {
        Object file = openFile(path);
        Object rawData = extractData(file);
        Object data = parseData(rawData);
        Object analysis = analyzeData(data);
        sendReport(analysis);
        closeFile(file);
    }

    public Object openFile(String path) {
        System.out.println("\nOpening file: " + path);
        return new Object(); // mock file object
    }

    public Object analyzeData(Object data) {
        System.out.println("Analyzing data...");
        return "Analysis result";
    }

    public void sendReport(Object analysis) {
        System.out.println("Generating report: " + analysis);
    }

    public void closeFile(Object file) {
        System.out.println("Closing file...\n");
    }

    // ABSTRACT STEPS
    public abstract Object extractData(Object file);
    public abstract Object parseData(Object rawData);
}


// SUBCLASSES
class DocDataMiner extends DataMining {

    @Override
    public Object extractData(Object file) {
        System.out.println("Extracting data from DOC file...");
        return "DOC Raw Data";
    }

    @Override
    public Object parseData(Object rawData) {
        System.out.println("Parsing DOC data...");
        return "DOC Parsed Data";
    }
}


class PDFDataMiner extends DataMining {

    @Override
    public Object extractData(Object file) {
        System.out.println("Extracting data from PDF file...");
        return "PDF Raw Data";
    }

    @Override
    public Object parseData(Object rawData) {
        System.out.println("Parsing PDF data...");
        return "PDF Parsed Data";
    }
}


class CSVDataMiner extends DataMining {

    @Override
    public Object extractData(Object file) {
        System.out.println("Extracting data from CSV file...");
        return "CSV Raw Data";
    }

    @Override
    public Object parseData(Object rawData) {
        System.out.println("Parsing CSV data...");
        return "CSV Parsed Data";
    }
}