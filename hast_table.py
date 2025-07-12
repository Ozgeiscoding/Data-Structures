TABLE_SIZE = 10

hash_table = [None] * TABLE_SIZE

def simple_hash(word):
    return ord(word[0]) % TABLE_SIZE

def insert(word):
    index = simple_hash(word)
    hash_table[index] = word
    print(f'"{word}" kelimesi {index}. index\'e yerleştirildi.')

def search(word):
    index = simple_hash(word)
    if hash_table[index] == word:
        print(f'"{word}" bulundu! Index: {index}')
    else:
        print(f'"{word}" bulunamadi')

# Ana program
insert("elma")
insert("muz")
insert("kiraz")

print("\nKelime arama:")
search("elma")    # olmalı
search("muz")     # olmalı
search("armut")   # yok