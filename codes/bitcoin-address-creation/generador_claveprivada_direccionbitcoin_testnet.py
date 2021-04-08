import os, binascii, hashlib, base58, ecdsa

def ripemd160(x):
    d = hashlib.new('ripemd160')
    d.update(x)
    return d

# generate private key
# 0 Private ECDSA Key
priv_key = os.urandom(32)
print(priv_key.encode('hex'))


# add the prefix for the WIF convertion por defecto para la main network es \x80         2
ptwifprefix = '\xEF' + priv_key
print(ptwifprefix.encode('hex'))

# SHA-256 hash de lo anterior                                                            3
wif1sha256 = hashlib.sha256(ptwifprefix)
print(wif1sha256.digest().encode('hex'))

# SHA-256 hash de lo anterior                                                            4
wif2sha256 = hashlib.sha256(wif1sha256.digest())                                         
print(wif2sha256.digest().encode('hex'))

 #First 4 bytes of 4, this is the checksum
wifchecksum = wif2sha256.digest()[:4]
print( wifchecksum.encode('hex') )

# Adding 5 at the end of 2
addwifchecksum = ptwifprefix + wifchecksum
print( addwifchecksum.encode('hex') )

# Base58 encoding of 6
WIF = base58.b58encode( addwifchecksum )
print("Wallet Import Format " + WIF)

print("")

# 1 Public ECDSA Key
sk = ecdsa.SigningKey.from_string(priv_key, curve=ecdsa.SECP256k1)
vk = sk.verifying_key
pubKey=('\04'+sk.verifying_key.to_string()) # Cambiar el prefijo en caso de tesnet
print( pubKey.encode('hex') )

# 2 SHA-256 hash of 1
#pubKey="04657F59FCAD807ACC3A05EFC9EC35EEDAB6A4663AB0FA4DA7AFAA7ADCA9522D80C4C8CFA13C303B0577E8FF5A25B56C40630DA6C970A6E1696EF960EFD5DE39F7"
ptafirstsha256 = hashlib.sha256(pubKey)
print( ptafirstsha256.digest().encode('hex') )

# 3 RIPEMD-160 Hash of 2
hash160 = ripemd160( ptafirstsha256.digest() )
print( hash160.digest().encode('hex') )

# 4 Adding network bytes to 3
ptaprefix = '\x6f'+hash160.digest()   # cambiar el prefijo dependiendo de la red
print( ptaprefix.encode('hex') )

# 5  SHA-256 hash of 4
ptasecondsha256 = hashlib.sha256(ptaprefix)
print(ptasecondsha256.digest().encode('hex'))

# SHA-256 hash of 5
ptathirdsha256 = hashlib.sha256(ptasecondsha256.digest())
print(ptathirdsha256.digest().encode('hex') )

# 7 - First four bytes of 6
checksum = ptathirdsha256.digest()[:4]
print( checksum.encode('hex') )

# 8 Adding 7 at the end of 4
addchecksum = ptaprefix + checksum
print( addchecksum.encode('hex') )

# 9 Base58 encoding of 8
public_address = base58.b58encode( addchecksum )
print( public_address )

