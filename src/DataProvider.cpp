class DataProvider {
    public:
        virtual GDALDataset* GetDataSet();
        virtual void GetMetadata();
        virtual void isEmpty();
    private:
        const char* url;

};