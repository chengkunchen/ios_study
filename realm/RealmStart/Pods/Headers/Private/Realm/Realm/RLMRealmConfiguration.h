////////////////////////////////////////////////////////////////////////////
//
// Copyright 2015 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#import <Foundation/Foundation.h>
#import <Realm/RLMRealm.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An `RLMRealmConfiguration` instance describes the different options used to
 create an instance of a Realm.

 `RLMRealmConfiguration` instances are just plain `NSObject`s. Unlike `RLMRealm`s
 and `RLMObject`s, they can be freely shared between threads as long as you do not
 mutate them.
 
 Creating configuration objects for class subsets (by setting the
 `objectClasses` property) can be expensive. Because of this, you will normally want to
 cache and reuse a single configuration object for each distinct configuration rather than 
 creating a new object each time you open a Realm.
 */
@interface RLMRealmConfiguration : NSObject<NSCopying>

#pragma mark - Default Configuration

/**
 Returns the default configuration used to create Realms when no other
 configuration is explicitly specified (i.e. `+[RLMRealm defaultRealm]`).

 @return The default Realm configuration.
 */
+ (instancetype)defaultConfiguration;

/**
 Sets the default configuration to the given `RLMRealmConfiguration`.

 @param configuration The new default Realm configuration.
 */
+ (void)setDefaultConfiguration:(RLMRealmConfiguration *)configuration;

#pragma mark - Properties

/// The local URL of the Realm file. Mutually exclusive with `inMemoryIdentifier`.
@property (nonatomic, copy, nullable) NSURL *fileURL;

/// A string used to identify a particular in-memory Realm. Mutually exclusive with `path`.
@property (nonatomic, copy, nullable) NSString *inMemoryIdentifier;

/// A 64-byte key to use to encrypt the data, or `nil` if encryption is not enabled.
@property (nonatomic, copy, nullable) NSData *encryptionKey;

/// Whether the Realm is read-only (must be `YES` for read-only files).
@property (nonatomic) BOOL readOnly;

/// The current schema version.
@property (nonatomic) uint64_t schemaVersion;

/// The block which migrates the Realm to the current version.
@property (nonatomic, copy, nullable) RLMMigrationBlock migrationBlock;

/**
 Whether to recreate the Realm file with the provided schema if a migration is required.
 This is the case when the stored schema differs from the provided schema or
 the stored schema version differs from the version on this configuration.
 Setting this property to `YES` deletes the file if a migration would otherwise be required or executed.

 @note Setting this property to `YES` doesn't disable file format migrations.
 */
@property (nonatomic) BOOL deleteRealmIfMigrationNeeded;

/// The classes persisted in the Realm.
@property (nonatomic, copy, nullable) NSArray *objectClasses;

@end

NS_ASSUME_NONNULL_END
