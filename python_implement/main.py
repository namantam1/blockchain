from hashlib import sha256
from time import time
from dataclasses import dataclass, asdict
import json
from typing import List

class Block:
    def __init__(
        self,
        data: dict = None,
        timestamp: float = time(),
        hash: str = None,
        previousHash: str = None,
        pow: int = 0
    ):
        self.data = data
        self.hash = hash
        self.previousHash = previousHash
        self.timestamp = timestamp
        self.pow = pow
    
    def __str__(self):
        return json.dumps(dict(
            data=self.data,
            hash=self.hash,
            previousHash=self.previousHash,
            timestamp=self.timestamp,
            pow=self.pow
        ))
    
    def __repr__(self):
        return self.__str__()
    
    def calculate_hash(self) -> str:
        string = str(self.previousHash) + str(self.data) + str(self.timestamp) + str(self.pow)
        return sha256(string.encode()).hexdigest()

    def mine(self, difficulty):
        while(self.hash is None or self.hash[:difficulty] != '0' * difficulty):
            self.pow += 1
            self.hash = self.calculate_hash()


class BlockChain:
    genesisBlock: Block = None
    chain: List[Block] = []
    difficulty: int = 0

    def __init__(self, difficulty=2) -> "BlockChain":
        self.genesisBlock = Block(hash="0")
        self.chain.append(self.genesisBlock)
        self.difficulty = difficulty

    def add_block(self, data: dict):
        latest_block = self.chain[-1]
        new_block = Block(data, previousHash=latest_block.hash)
        new_block.mine(self.difficulty)
        self.chain.append(new_block)

    def is_valid(self) -> bool:
        for i in range(len(self.chain) - 1):
            previous_block = self.chain[i]
            current_block = self.chain[i+1]
            if current_block.hash != current_block.calculate_hash()\
                or current_block.previousHash != previous_block.hash:
                return False
        return True

@dataclass
class Payment:
    _from: str
    _to: str
    _amount: float

    def to_dict(self):
        return asdict(self)


if __name__ == "__main__":
    block_chain = BlockChain()
    block_chain.add_block(Payment("Naman", "Jhon", 100.22).to_dict())
    block_chain.add_block(Payment("Jhon", "Abraham", 20.666).to_dict())
    block_chain.add_block(Payment("Jhon", "Naman", 200.569).to_dict())
    # for i in block_chain.chain:
    #     print(i)
    print(block_chain.is_valid())
