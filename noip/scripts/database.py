
from pymongo import MongoClient

COLLECTION_NAME = 'luogu'


def init_db():
    client = MongoClient('localhost', 27017)
    client.spider.drop_collection(COLLECTION_NAME)
    client.spider.create_collection(COLLECTION_NAME)
    collection = client.spider[COLLECTION_NAME]
    collection.create_index("index", unique=True)
    return collection


client = MongoClient('localhost', 27017)
db = client.spider[COLLECTION_NAME]


def get_problem(index):
    return db.find({'index': index})