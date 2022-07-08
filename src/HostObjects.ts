import type { BinaryLike } from './types';

export interface Hash {
  update(data: BinaryLike): void;
  finalize(): string;
}
