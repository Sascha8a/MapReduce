from MapReduce import Worker

def clean(word):
    word = word.replace(".", "")
    word = word.replace(",", "")
    word = word.replace("'", "")
    word = word.replace('"', "")
    word = word.replace("!", "")
    word = word.replace(";", "")
    word = word.replace("?", "")
    word = word.replace(")", "")
    word = word.replace("(", "")
    word = word.replace(":", "")
    word = word.replace("1", "")
    word = word.replace("2", "")
    word = word.replace("3", "")
    word = word.replace("4", "")
    word = word.replace("5", "")
    word = word.replace("6", "")
    word = word.replace("7", "")
    word = word.replace("8", "")
    word = word.replace("9", "")
    word = word.replace("0", "")
    word = word.lower()
    word = word.strip()
    word = word.encode(encoding='UTF-8',errors='ignore').decode('utf-8')
    return word

def map_func(chunk):
    result_dict = {}
    results = []

    for word in str(chunk).split(' '):
        word = clean(word)
        if (word in result_dict):
            result_dict[word] += 1
        else:
            result_dict[word] = 1

    for key, value in result_dict.items():
        if (key != ""):
            print(key)
            results.append([key, value])

    return results

def reduce_func(key, values):
    return sum(values)


Worker(map_func, reduce_func)
